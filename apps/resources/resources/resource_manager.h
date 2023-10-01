#pragma once
#include <asset-bundler/bundle.h>

namespace wind {
    namespace resources {
        class _internal {
        public:
            static vector<assets::Bundle*> bundles;
        };

        void addBundle(assets::Bundle*);

        //===================================================//

        template <typename T>
        T* get(const char* name);

        template <typename T>
        requires requires (T* t) {
            {t} -> std::convertible_to<assets::ISerializable*>;
        }
        T* get(const char* _name) {
            for (auto bundle : _internal::bundles)
                if (auto res = bundle->getResource<T>(_name))
                    return res;

            return nullptr;
        }

        template <typename T>
        T* get(const char* _name) {
            log().error() << "Not found function for load type: [" << typeid(T).name() << "] resource name: [" << _name << "]"; 
            return nullptr;
        }

        //===================================================//
    }
}