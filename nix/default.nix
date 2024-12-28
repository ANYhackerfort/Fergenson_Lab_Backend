{
  cmake,
  libtorch-bin,
  boost,
  opencv,
  liboai,
  meson,
  ninja,
  pkg-config,
  llvmPackages_19,
  grpc,
  lib,
}:
llvmPackages_19.stdenv.mkDerivation (finalAttrs: {
  pname = "WebSocketWithOpenCV";
  version = "0.1.0";

  src = ../.;

  nativeBuildInputs = [
    meson
    ninja
    cmake
    pkg-config
  ];

  buildInputs = [
    boost
    opencv
    libtorch-bin
    liboai
    grpc
  ];

  installPhase = ''
    mkdir -p $out/bin
    cp WebSocketWithOpenCV $out/bin
  '';

  meta = {
    maintainers = [ lib.maintainers.youwen5 ];
    mainProgram = "WebSocketWithOpenCV";
  };
})
