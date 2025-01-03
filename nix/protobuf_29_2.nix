{
  lib,
  stdenv,
  abseil-cpp,
  buildPackages,
  cmake,
  fetchFromGitHub,
  fetchpatch,
  gtest,
  zlib,
  versionCheckHook,

  # downstream dependencies
  python3,
  grpc,
  enableShared ? !stdenv.hostPlatform.isStatic,

  testers,
  ...
}:

stdenv.mkDerivation (finalAttrs: {
  pname = "protobuf";
  version = "29.2";

  src = fetchFromGitHub {
    owner = "protocolbuffers";
    repo = "protobuf";
    tag = "v${finalAttrs.version}";
    hash = "sha256-zClgj7m0JK2PNWi/1kA2L+HklzaHoT09KwnVt7Rm4ks=";
  };

  postPatch = lib.optionalString stdenv.hostPlatform.isDarwin ''
    substituteInPlace src/google/protobuf/testing/googletest.cc \
      --replace 'tmpnam(b)' '"'$TMPDIR'/foo"'
  '';

  patches = lib.optionals (lib.versionOlder finalAttrs.version "22") [
    # fix protobuf-targets.cmake installation paths, and allow for CMAKE_INSTALL_LIBDIR to be absolute
    # https://github.com/protocolbuffers/protobuf/pull/10090
    (fetchpatch {
      url = "https://github.com/protocolbuffers/protobuf/commit/a7324f88e92bc16b57f3683403b6c993bf68070b.patch";
      hash = "sha256-SmwaUjOjjZulg/wgNmR/F5b8rhYA2wkKAjHIOxjcQdQ=";
    })
  ];

  nativeBuildInputs =
    [
      cmake
    ]
    ++ lib.optionals (stdenv.hostPlatform != stdenv.buildPlatform) [
      # protoc of the same version must be available for build. For non-cross builds, it's able to
      # re-use the executable generated as part of the build
      buildPackages."protobuf_${lib.versions.major finalAttrs.version}"
    ];

  buildInputs = [
    gtest
    zlib
  ];

  propagatedBuildInputs = [
    abseil-cpp
  ];

  strictDeps = true;

  cmakeDir = if lib.versionOlder finalAttrs.version "22" then "../cmake" else null;
  cmakeFlags =
    [
      "-Dprotobuf_USE_EXTERNAL_GTEST=ON"
      "-Dprotobuf_ABSL_PROVIDER=package"
    ]
    ++ lib.optionals enableShared [
      "-Dprotobuf_BUILD_SHARED_LIBS=ON"
    ]
    ++ lib.optionals (!finalAttrs.finalPackage.doCheck) [
      "-Dprotobuf_BUILD_TESTS=OFF"
    ];

  doCheck =
    # Tests fail to build on 32-bit platforms; fixed in 22.x
    # https://github.com/protocolbuffers/protobuf/issues/10418
    # Also AnyTest.TestPackFromSerializationExceedsSizeLimit fails on 32-bit platforms
    # https://github.com/protocolbuffers/protobuf/issues/8460
    !stdenv.hostPlatform.is32bit;

  nativeInstallCheckInputs = [
    versionCheckHook
  ];
  versionCheckProgram = [ "${placeholder "out"}/bin/protoc" ];
  versionCheckProgramArg = [ "--version" ];
  doInstallCheck = true;

  meta = {
    description = "Google's data interchange format";
    longDescription = ''
      Protocol Buffers are a way of encoding structured data in an efficient
      yet extensible format. Google uses Protocol Buffers for almost all of
      its internal RPC protocols and file formats.
    '';
    license = lib.licenses.bsd3;
    platforms = lib.platforms.all;
    homepage = "https://protobuf.dev/";
    maintainers = with lib.maintainers; [ GaetanLepage ];
    mainProgram = "protoc";
  };
})
