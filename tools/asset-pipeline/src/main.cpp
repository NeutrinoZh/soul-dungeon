#include <asset-pipeline/pipes-register.h>
#include <asset-pipeline/pipes/content-3d-pipe.h>
#include <asset-pipeline/pipes/default-pipe.h>
#include <asset-pipeline/pipes/img-pipe.h>
#include <asset-pipeline/pipes/shader-pipe.h>
#include <spdlog/spdlog.h>

int main(int argc, char** argv) {
    using namespace wind;

    const fs::path source = argc > 1 ? argv[1] : fs::current_path() / "asset/";
    const fs::path destination = argc > 2 ? argv[2] : fs::current_path() / "default.bundle";
    const fs::path cache = argc > 3 ? argv[3] : fs::current_path() / ".cache/";

    spdlog::info("Source directory: {}", source.string());
    spdlog::info("Destination bundle path: {}", destination.string());
    spdlog::info("Cache directory: {}", cache.string());

    asset_pipeline::PipeRegister::regPipe(".*\\.jpg", new asset_pipeline::ImgPipe());
    asset_pipeline::PipeRegister::regPipe(".*\\.obj", new asset_pipeline::Content3DPipe());
    asset_pipeline::PipeRegister::regPipe(".*\\.glsl", new asset_pipeline::ShaderPipe());
    asset_pipeline::PipeRegister::regPipe(".*\\.*", new asset_pipeline::DefaultPipe());

    asset_pipeline::AssetPipeline pipeline;
    pipeline.setConfig(source / ".import-config");
    pipeline.compileDirectory(source, cache);
    pipeline.clearUnusedCache(source, cache);
    pipeline.linkDirectory(cache, destination);

    return EXIT_SUCCESS;
}