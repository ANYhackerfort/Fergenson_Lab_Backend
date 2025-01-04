project(
    'WebSocketWithOpenCV',
    'cpp',
    version: '0.1',
    default_options: ['cpp_std=c++17', 'b_pie=true'],
)

# Include directories
inc_dirs = include_directories('include', 'protos')

# Dependencies
opencv_dep = dependency('opencv4', required: false)
if not opencv_dep.found()
    opencv_dep = dependency('opencv')
endif

boost_dep = dependency('boost')
torch_dep = dependency('Torch')
grpc_dep = dependency('grpc++')
protobuf_dep = dependency('protobuf')
nlohmann_dep = dependency('nlohmann_json')

# Add source files
sources = [
    'src/websocket_s/websocket_server.cpp',
    'src/openCV_s/process_image.cpp',
    'src/stateOfLab_s/state_of_lab.cpp',
]

# Add proto-generated files
proto_sources = ['protos/message.pb.cc', 'protos/message.grpc.pb.cc']

# Add all sources together
all_sources = sources + proto_sources

# Create executable target
executable(
    'WebSocketWithOpenCV',
    all_sources,
    include_directories: inc_dirs,
    dependencies: [boost_dep, opencv_dep, torch_dep, grpc_dep, protobuf_dep],
)
