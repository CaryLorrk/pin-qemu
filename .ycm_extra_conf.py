import os
import ycm_core
from clang_helpers import PrepareClangFlags

flags = [
'-x', 'c',
'-std', 'c99',
'-DHAVE_CONFIG_H',
'-DNEED_CPU_H',
'-DPIE',
'-D_FILE_OFFSET_BITS=64',
'-D_FORTIFY_SOURCE=2',
'-D_GNU_SOURCE',
'-D_LARGEFILE_SOURCE',
'-I/local/carywu/pin/lib/glib-2.12.0/include/glib-2.0',
'-I/local/carywu/pin/lib/glib-2.12.0/lib/glib-2.0/include',
'-I./src',
'-I./src/block',
'-I./src/disas',
'-I./src/dtc',
'-I./src/dtc/libfdt',
'-I./src/fpu',
'-I./src/hw/core',
'-I./src/include',
'-I./src/linux-headers',
'-I./src/linux-user',
'-I./src/linux-user/arm',
'-I./src/linux-user/arm/nwfpe',
'-I./src/pixman/pixman',
'-I./src/pixman/test',
'-I./src/qapi',
'-I./src/qga',
'-I./src/qobject',
'-I./src/qom',
'-I./src/stubs',
'-I./src/target-arm',
'-I./src/tcg',
'-I./src/tcg/i386',
'-I./src/tests',
'-I./src/trace',
'-I./src/util',
'-I./temp/test/dtc',
'-I./temp/test/linux-headers',
'-I./temp/test/pixman/pixman',
'-I./temp/test/pixman',
'-I./temp/test',
'-I./temp/test/arm-linux-user',
'-I./temp/test/pixman/test',
'-I./temp/test/qga/qapi-generated',
'-I./temp/test/block',
'-I./temp/test/disas',
'-I./temp/test/arm-linux-user/fpu',
'-I./temp/test/hw/core',
'-I./temp/test/arm-linux-user',
'-I./temp/test/arm-linux-user/linux-user',
'-I./temp/test/arm-linux-user/linux-user/arm/nwfpe',
'-I./temp/test/qapi',
'-I./temp/test/trace',
'-I./temp/test/linux-headers',
'-I./temp/test/qga',
'-I./temp/test/qobject',
'-I./temp/test/util',
'-I./temp/test/qom',
'-I./temp/test/stubs',
'-I./temp/test/arm-linux-user/target-arm',
'-I./temp/test/arm-linux-user/tcg'
]

# Set this to the absolute path to the folder (NOT the file!) containing the
# compile_commands.json file to use that instead of 'flags'. See here for
# more details: http://clang.llvm.org/docs/JSONCompilationDatabase.html
#
# Most projects will NOT need to set this to anything; you can just change the
# 'flags' list of compilation flags. Notice that YCM itself uses that approach.
compilation_database_folder = ''

if compilation_database_folder:
  database = ycm_core.CompilationDatabase( compilation_database_folder )
else:
  database = None


def DirectoryOfThisScript():
  return os.path.dirname( os.path.abspath( __file__ ) )


def MakeRelativePathsInFlagsAbsolute( flags, working_directory ):
  if not working_directory:
    return flags
  new_flags = []
  make_next_absolute = False
  path_flags = [ '-isystem', '-I', '-iquote', '--sysroot=' ]
  for flag in flags:
    new_flag = flag

    if make_next_absolute:
      make_next_absolute = False
      if not flag.startswith( '/' ):
        new_flag = os.path.join( working_directory, flag )

    for path_flag in path_flags:
      if flag == path_flag:
        make_next_absolute = True
        break

      if flag.startswith( path_flag ):
        path = flag[ len( path_flag ): ]
        new_flag = path_flag + os.path.join( working_directory, path )
        break

    if new_flag:
      new_flags.append( new_flag )
  return new_flags


def FlagsForFile( filename ):
  if database:
    # Bear in mind that compilation_info.compiler_flags_ does NOT return a
    # python list, but a "list-like" StringVec object
    compilation_info = database.GetCompilationInfoForFile( filename )
    final_flags = PrepareClangFlags(
        MakeRelativePathsInFlagsAbsolute(
            compilation_info.compiler_flags_,
            compilation_info.compiler_working_dir_ ),
        filename )

    # NOTE: This is just for YouCompleteMe; it's highly likely that your project
    # does NOT need to remove the stdlib flag. DO NOT USE THIS IN YOUR
    # ycm_extra_conf IF YOU'RE NOT 100% YOU NEED IT.
    try:
      final_flags.remove( '-stdlib=libc++' )
    except ValueError:
      pass
  else:
    relative_to = DirectoryOfThisScript()
    final_flags = MakeRelativePathsInFlagsAbsolute( flags, relative_to )

  return {
    'flags': final_flags,
    'do_cache': True
  }
