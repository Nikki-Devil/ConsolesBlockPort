# all sources except ./Platform/*
client_sources = run_command(
  'sh', '-c',
  'find "'
    + meson.current_source_dir()
    + '" \\( -name "*.cpp" -o -name "*.c" \\) ! -path "*/Platform/*"',
  check : true,
).stdout().strip().split('\n')

# all sources in ./Platform (top-level files only)
platform_sources = run_command(
  'sh', '-c',
  'find "'
    + meson.current_source_dir() / 'Platform'
    + '" -maxdepth 1 \\( -name "*.cpp" -o -name "*.c" \\)',
  check : true,
).stdout().strip().split('\n')

# some platform-specific sources that are for some stupid reason in Common
exclude_platform_common_sources = [
  ' ! -path "*/Network/Sony/*"',
  ' ! -path "*/XUI/*"',
  ' ! -path "*/zlib/*"',
]

# all sources in in ./Platform/Common
platform_sources += run_command(
  'sh', '-c',
  'find "'
    + meson.current_source_dir() / 'Platform/Common'
    + '" \\( -name "*.cpp" -o -name "*.c" \\)'
    + ' '.join(exclude_platform_common_sources),
  check : true,
).stdout().strip().split('\n')

# linux-specific files (everything in Platform/Linux)
if host_machine.system() == 'linux'
  platform_sources += run_command(
    'sh', '-c',
    'find "'
      + meson.current_source_dir() / 'Platform/Linux'
      + '" \\( -name "*.cpp" -o -name "*.c" \\) ',
    check : true,
  ).stdout().strip().split('\n')
endif

executable('Minecraft.Client',
  client_sources + platform_sources + localisation[1],
  include_directories : include_directories('Platform'),
  dependencies : [
    render_dep,
    input_dep,
    profile_dep,
    storage_dep,
    assets_localisation_dep,
    world_dep,
    gl_dep,
    glu_dep,
    glfw_dep,
    thread_dep,
    dl_dep,
    dependency('zlib'),
  ],
  cpp_args : global_cpp_args + global_cpp_defs + [
    '-DUNICODE', '-D_UNICODE',
    '-include', meson.current_source_dir() / 'Platform/stdafx.h',
  ],
  c_args   : global_cpp_defs + ['-DUNICODE', '-D_UNICODE'],
  install  : true,
  install_dir : ''
)

