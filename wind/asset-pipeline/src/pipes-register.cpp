#include <asset-pipeline/pipes-register.h>
#include <spdlog/spdlog.h>

#include <regex>

namespace wind {
namespace asset_pipeline {

std::vector<std::regex> PipeRegister::m_regexs{};
std::vector<AssetPipe*> PipeRegister::m_pipes{};

AssetPipe* PipeRegister::getPipe(fs::path _path) {
  assert(m_regexs.size() != m_pipes.size());

  auto path = _path.string();
  for (size_t i = 0; i < m_regexs.size(); ++i)
    if (std::regex_match(path.c_str(), m_regexs[i]))
      return m_pipes[i];

  return nullptr;
}

AssetPipe* PipeRegister::getPipe(const std::string& _name) {
  for (auto pipe : m_pipes)
    if (pipe->id() == _name)
      return pipe;

  return nullptr;
}

void PipeRegister::regPipe(const char* _regex, AssetPipe* _pipe) {
  try {
    auto regex = std::regex(_regex);
    m_pipes.push_back(_pipe);
    m_regexs.push_back(regex);

    spdlog::info("PipeRegister: registered pipe: {} for '{}'", _pipe->id(), _regex);
  } catch (std::regex_error& ex) {
    spdlog::error("PipeRegister: cannot create regex '{}': {}", _regex, ex.what());
  }
}

} // namespace asset_pipeline
} // namespace wind