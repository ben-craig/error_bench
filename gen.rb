TEST_DIRS = [
    {:dir => "wont_throw", :cc_flags => ""},
    {:dir => "may_throw", :cc_flags => "/EHsc"},
]

def scrub_name(fname)
    return fname.gsub(" ","_").gsub("/","")
end

class TestCase
    def initialize(t, proc, flags)
        @src_info = t
        @proc = proc
        @scenario_cc_flags = flags
        # TODO!!!
        @dest = "#{@proc}\\#{scrub_name(flags)}\\#{@src_info[:dir]}"
        @flags = "    EXTRA_FLAGS = " + @src_info[:cc_flags] + " " + @scenario_cc_flags + "\n"
        @cc = "#{@proc}_compile"
    end
    def dir; @src_info[:dir]; end
    def proc; @proc; end
    def dest; @dest; end
    def flags; @flags; end
    def cc; @cc; end
end

def each_case
    ["x86", "x64"].each do |proc|
        ["/MT", "/MD"].each do |flags|
            TEST_DIRS.each do |t|
                yield TestCase.new(t, proc, flags)
            end
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
    file.print "build #{dest_dir}\\dtor.obj: #{cc} common\\dtor.cpp\n"
    file.print cc_flags
    file.print "build #{dest_dir}\\caller.obj: #{cc} #{dir}\\caller.cpp\n"
    file.print cc_flags
    file.print "build #{dest_dir}\\callee.obj: #{cc} #{dir}\\callee.cpp\n"
    file.print cc_flags
    file.print "build #{dest_dir}\\bench.obj: #{cc} #{dir}\\bench.cpp\n"
    file.print cc_flags
    file.print "build #{dest_dir}\\main.obj: #{cc} #{dir}\\main.cpp\n"
    file.print cc_flags


    file.print "build #{dest_dir}\\main.exe | #{dest_dir}\\main.exe.map: #{test_case.proc}_map_link $\n"
    file.print "    #{dest_dir}\\main.obj $\n"
    file.print "    #{dest_dir}\\caller.obj $\n"
    file.print "    #{dest_dir}\\callee.obj $\n"
    file.print "    #{dest_dir}\\dtor.obj\n\n"

    file.print "build #{dest_dir}\\bench.exe : #{test_case.proc}_link $\n"
    file.print "    #{dest_dir}\\bench.obj $\n"
    file.print "    #{dest_dir}\\caller.obj $\n"
    file.print "    #{dest_dir}\\callee.obj $\n"
    file.print "    #{dest_dir}\\dtor.obj\n\n"

    file.print "build #{dest_dir}\\main.exe.asm: asm_dump #{dest_dir}\\main.exe\n"
    file.print "build #{dest_dir}\\bench.exe.asm: asm_dump #{dest_dir}\\bench.exe\n"

    file.print "build #{dest_dir}\\main.size: measure_size #{dest_dir}\\main.exe.map | $\n"
    file.print "    #{dest_dir}\\main.exe.asm $\n"
    file.print "    #{dest_dir}\\bench.exe.asm\n\n"
end

def main()
    File.open("generated_targets_from_gen.rb.ninja", "w") do |h|
        h.print "ninja_required_version = 1.7\n\n"
        each_case do |c|
            gen_config(h, c)
        end

        h.print "build totals\\sizes.csv: collect_sizes"
        each_case do |c|
            h.print " #{c.dest}\\main.size"
        end
        h.print "\n\n"
        h.print "build totals\\times.csv: collect_benches"
        each_case do |c|
            h.print " #{c.dest}\\bench.exe"
        end
        h.print " | totals\\sizes.csv\n\n"

        h.print "default totals\\times.csv\n"
    end
end

if __FILE__ == $0
   main()
end
