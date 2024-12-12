project(
  'WebSocketWithOpenCV',
  'cpp',
  version: '0.1',
  default_options: ['cpp_std=c++17'],
)

inc_dirs = include_directories('include', 'include/openCV_f')

opencv_dep = dependency('opencv4', method: 'auto', required: false)
if not opencv_dep.found()
  opencv_dep = dependency('opencv', method: 'auto', required: true)
endif

boost_dep = dependency('boost', method: 'auto', required: true)
torch_dep = dependency('Torch', method: 'auto', required: true)

liboai_dep = dependency('oai', method: 'auto', required: true)

libcurl_dep = dependency('libcurl', method: 'auto', required: true)
nlohmann_dep = dependency('nlohmann_json', method: 'auto', required: true)

# Add source files
sources = [
  'src/websocket_s/websocket_server.cpp',
  'src/openCV_s/process_image.cpp',
]

# Create executable target
executable(
  'WebSocketWithOpenCV',
  sources,
  include_directories: inc_dirs,
  dependencies: [boost_dep, opencv_dep, torch_dep, liboai_dep, libcurl_dep, nlohmann_dep],
)
