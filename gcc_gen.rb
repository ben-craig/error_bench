TEST_DIRS = [
    {:dir => "one_catch/throw_val", :cc_flags => ""},
    {:dir => "one_catch/throw_struct", :cc_flags => ""},
    {:dir => "one_catch/throw_exception", :cc_flags => ""},
    {:dir => "one_catch/tls_error_val", :cc_flags => "-fno-exceptions"},
    {:dir => "one_catch/tls_error_struct", :cc_flags => "-fno-exceptions"},
    {:dir => "one_catch/return_val", :cc_flags => "-fno-exceptions"},
    {:dir => "one_catch/return_struct", :cc_flags => "-fno-exceptions"},
    {:dir => "one_catch/ref_struct", :cc_flags => "-fno-exceptions"},
    {:dir => "one_catch/ref_val", :cc_flags => "-fno-exceptions"},
    {:dir => "one_catch/expected_struct", :cc_flags => "-fno-exceptions"},
    {:dir => "one_catch/expected_val", :cc_flags => "-fno-exceptions"},
    {:dir => "two_catch/throw_val", :cc_flags => ""},
    {:dir => "two_catch/throw_struct", :cc_flags => ""},
    {:dir => "two_catch/throw_exception", :cc_flags => ""},
    {:dir => "two_catch/tls_error_val", :cc_flags => "-fno-exceptions"},
    {:dir => "two_catch/tls_error_struct", :cc_flags => "-fno-exceptions"},
    {:dir => "two_catch/return_val", :cc_flags => "-fno-exceptions"},
    {:dir => "two_catch/return_struct", :cc_flags => "-fno-exceptions"},
    {:dir => "two_catch/ref_struct", :cc_flags => "-fno-exceptions"},
    {:dir => "two_catch/ref_val", :cc_flags => "-fno-exceptions"},
    {:dir => "two_catch/expected_struct", :cc_flags => "-fno-exceptions"},
    {:dir => "two_catch/expected_val", :cc_flags => "-fno-exceptions"},
    {:dir => "one_neutral/terminate", :cc_flags => "-fno-exceptions"},
    {:dir => "one_neutral/throw_val", :cc_flags => ""},
    {:dir => "one_neutral/throw_struct", :cc_flags => ""},
    {:dir => "one_neutral/throw_exception", :cc_flags => ""},
    {:dir => "one_neutral/noexcept_terminate", :cc_flags => ""},
    {:dir => "one_neutral/tls_error_val", :cc_flags => "-fno-exceptions"},
    {:dir => "one_neutral/tls_error_struct", :cc_flags => "-fno-exceptions"},
    {:dir => "one_neutral/return_val", :cc_flags => "-fno-exceptions"},
    {:dir => "one_neutral/return_struct", :cc_flags => "-fno-exceptions"},
    {:dir => "one_neutral/ref_struct", :cc_flags => "-fno-exceptions"},
    {:dir => "one_neutral/ref_val", :cc_flags => "-fno-exceptions"},
    {:dir => "one_neutral/expected_struct", :cc_flags => "-fno-exceptions"},
    {:dir => "one_neutral/expected_val", :cc_flags => "-fno-exceptions"},
    {:dir => "two_neutral/terminate", :cc_flags => "-fno-exceptions"},
    {:dir => "two_neutral/throw_val", :cc_flags => ""},
    {:dir => "two_neutral/throw_struct", :cc_flags => ""},
    {:dir => "two_neutral/throw_exception", :cc_flags => ""},
    {:dir => "two_neutral/noexcept_terminate", :cc_flags => ""},
    {:dir => "two_neutral/tls_error_val", :cc_flags => "-fno-exceptions"},
    {:dir => "two_neutral/tls_error_struct", :cc_flags => "-fno-exceptions"},
    {:dir => "two_neutral/return_val", :cc_flags => "-fno-exceptions"},
    {:dir => "two_neutral/return_struct", :cc_flags => "-fno-exceptions"},
    {:dir => "two_neutral/ref_struct", :cc_flags => "-fno-exceptions"},
    {:dir => "two_neutral/ref_val", :cc_flags => "-fno-exceptions"},
    {:dir => "two_neutral/expected_struct", :cc_flags => "-fno-exceptions"},
    {:dir => "two_neutral/expected_val", :cc_flags => "-fno-exceptions"},
    {:dir => "one_error/terminate", :cc_flags => "-fno-exceptions"},
    {:dir => "one_error/throw_val", :cc_flags => ""},
    {:dir => "one_error/throw_struct", :cc_flags => ""},
    {:dir => "one_error/throw_exception", :cc_flags => ""},
    {:dir => "one_error/noexcept_terminate", :cc_flags => ""},
    {:dir => "one_error/tls_error_val", :cc_flags => "-fno-exceptions"},
    {:dir => "one_error/tls_error_struct", :cc_flags => "-fno-exceptions"},
    {:dir => "one_error/return_val", :cc_flags => "-fno-exceptions"},
    {:dir => "one_error/return_struct", :cc_flags => "-fno-exceptions"},
    {:dir => "one_error/ref_struct", :cc_flags => "-fno-exceptions"},
    {:dir => "one_error/ref_val", :cc_flags => "-fno-exceptions"},
    {:dir => "one_error/expected_struct", :cc_flags => "-fno-exceptions"},
    {:dir => "one_error/expected_val", :cc_flags => "-fno-exceptions"},
    {:dir => "two_error/terminate", :cc_flags => "-fno-exceptions"},
    {:dir => "two_error/throw_val", :cc_flags => ""},
    {:dir => "two_error/throw_struct", :cc_flags => ""},
    {:dir => "two_error/throw_exception", :cc_flags => ""},
    {:dir => "two_error/noexcept_terminate", :cc_flags => ""},
    {:dir => "two_error/tls_error_val", :cc_flags => "-fno-exceptions"},
    {:dir => "two_error/tls_error_struct", :cc_flags => "-fno-exceptions"},
    {:dir => "two_error/return_val", :cc_flags => "-fno-exceptions"},
    {:dir => "two_error/return_struct", :cc_flags => "-fno-exceptions"},
    {:dir => "two_error/ref_struct", :cc_flags => "-fno-exceptions"},
    {:dir => "two_error/ref_val", :cc_flags => "-fno-exceptions"},
    {:dir => "two_error/expected_struct", :cc_flags => "-fno-exceptions"},
    {:dir => "two_error/expected_val", :cc_flags => "-fno-exceptions"},
]

class TestCase
    def initialize(t, proc)
        @src_info = t
        @proc = proc
        @dest = "#{@proc}/#{@src_info[:dir]}"
        @flags = "    EXTRA_FLAGS = " + @src_info[:cc_flags] + "\n"
        @cc = "compile"
        @dir = "src/#{@src_info[:dir]}"
    end
    def dir; @dir; end
    def proc; @proc; end
    def dest; @dest; end
    def flags; @flags; end
    def cc; @cc; end
end

def each_case
    ["x64"].each do |proc|
        TEST_DIRS.each do |t|
            yield TestCase.new(t, proc, "")
        end
    end
end

def gen_config(file, test_case)
    cc_flags = test_case.flags
    cc = test_case.cc
    dir = test_case.dir
    dest_dir = test_case.dest
    file.print "#===========================================================\n"
    file.print "# #{dest_dir}\n"
    file.print "#===========================================================\n"
    file.print "build #{dest_dir}/dtor.obj: #{cc} src/common/dtor.cpp\n"
    file.print cc_flags
    file.print "build #{dest_dir}/LinuxTimeLogger.obj: #{cc} src/common/LinuxTimeLogger.cpp\n"
    file.print cc_flags
    file.print "build #{dest_dir}/caller.obj: #{cc} #{dir}/caller.cpp\n"
    file.print cc_flags
    file.print "build #{dest_dir}/callee.obj: #{cc} #{dir}/callee.cpp\n"
    file.print cc_flags
    file.print "build #{dest_dir}/bench.obj: #{cc} #{dir}/bench.cpp\n"
    file.print cc_flags
    file.print "build #{dest_dir}/main.obj: #{cc} #{dir}/main.cpp\n"
    file.print cc_flags


    file.print "build #{dest_dir}/main.exe : link $\n"
    file.print "    #{dest_dir}/main.obj $\n"
    file.print "    #{dest_dir}/caller.obj $\n"
    file.print "    #{dest_dir}/callee.obj $\n"
    file.print "    #{dest_dir}/dtor.obj\n\n"

    file.print "build #{dest_dir}/bench.exe : link $\n"
    file.print "    #{dest_dir}/bench.obj $\n"
    file.print "    #{dest_dir}/caller.obj $\n"
    file.print "    #{dest_dir}/callee.obj $\n"
    file.print "    #{dest_dir}/dtor.obj $\n"
    file.print "    #{dest_dir}/LinuxTimeLogger.obj\n"
    file.print "    EXTRA_FLAGS = -lrt\n\n"

    file.print "build #{dest_dir}/main.exe.asm: asm_dump #{dest_dir}/main.exe\n"
    file.print "build #{dest_dir}/bench.exe.asm: asm_dump #{dest_dir}/bench.exe\n"

    file.print "build #{dest_dir}/main.size: measure_size #{dest_dir}/main.exe.asm | $\n"
    file.print "    clang_measure_size.py\n"

    file.print "build #{dest_dir}/bench_padding: check_asm_padding #{dest_dir}/bench.exe.asm | $\n"
    file.print "    check_asm_alignment.py\n"
end

def main()
    File.open("build.ninja", "w") do |h|
        h.print "ninja_required_version = 1.7\n\n"
        h.print "include gcc.ninja\n\n"

        each_case do |c|
            gen_config(h, c)
        end

        h.print "build totals/sizes.csv: collect_sizes"
        each_case do |c|
            h.print " #{c.dest}/main.size"
        end
        h.print " | clang_concat_files.py\n\n"

        h.print "build totals/times.csv: collect_benches"
        each_case do |c|
            h.print " #{c.dest}/bench.exe"
        end
        h.print "\n\n"

        h.print "build padding: phony $\n"
        each_case do |c|
            h.print " #{c.dest}/bench_padding"
        end
        h.print "\n\n"

        h.print "build bench: phony totals/times.csv\n\n"

        h.print "default totals/sizes.csv\n"
    end
end

if __FILE__ == $0
   main()
end
