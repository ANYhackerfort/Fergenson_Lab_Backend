project(
  'WebSocketWithOpenCV',
  'cpp',
  version: '0.1',
  default_options: ['cpp_std=c++17', 'b_pie=true'],
)

# Include directories
inc_dirs = include_directories('include', 'include/openCV_f', 'protos')

# Dependencies
opencv_dep = dependency('opencv4', method: 'auto', required: false)
if not opencv_dep.found()
  opencv_dep = dependency('opencv', method: 'auto', required: true)
endif

boost_dep = dependency('boost', method: 'auto', required: true)
torch_dep = dependency('Torch', method: 'auto', required: true)
nlohmann_dep = dependency('nlohmann_json', method: 'auto', required: true)
grpc_dep = dependency('grpc++', method: 'auto', required: true)
protobuf_dep = dependency('protobuf', method: 'auto', required: true)

# Add source files
sources = [
  'src/websocket_s/websocket_server.cpp',
  'src/openCV_s/process_image.cpp',
]

# Add proto-generated files
proto_sources = [
  'protos/message.pb.cc',
  'protos/message.grpc.pb.cc',
]

# Add all sources together
all_sources = sources + proto_sources

# Create executable target
executable(
  'WebSocketWithOpenCV',
  all_sources,
  include_directories: inc_dirs,
  dependencies: [
    boost_dep,
    opencv_dep,
    torch_dep,
    nlohmann_dep,
    grpc_dep,
    protobuf_dep,
  ],
)
