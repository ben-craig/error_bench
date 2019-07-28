MAX_NOP_1 = 31
MAX_NOP_2 = 31

TERM_TYPES = [
    #{:dir => "terminate_________", :cc_flags => "/GR"},
    #{:dir => "noexcept_terminate", :cc_flags => "/GR /EHs"},
]
ERROR_TYPES = [
    {:dir => "throw_val_________", :cc_flags => "/GR /EHs"},
    {:dir => "throw_struct______", :cc_flags => "/GR /EHs"},
    {:dir => "throw_exception___", :cc_flags => "/GR /EHs"},
    {:dir => "tls_error_val_____", :cc_flags => "/GR"},
    {:dir => "tls_error_struct__", :cc_flags => "/GR"},
    {:dir => "return_val________", :cc_flags => "/GR"},
    {:dir => "return_struct_____", :cc_flags => "/GR"},
    {:dir => "ref_struct________", :cc_flags => "/GR"},
    {:dir => "ref_val___________", :cc_flags => "/GR"},
    {:dir => "expected_struct___", :cc_flags => "/GR"},
    {:dir => "expected_val______", :cc_flags => "/GR"},
    {:dir => "outcome_struct____", :cc_flags => "/GR-"},
    {:dir => "outcome_val_______", :cc_flags => "/GR-"},
    {:dir => "outcome_std_error_", :cc_flags => "/GR-"},
]
FULL_CASE_NAMES =   ["one_neutral", "two_neutral", "one_error__", "two_error__"]
NO_TERM_CASE_NAME = ["one_catch__", "two_catch__"]
BENCH_CASE_NAMES = ["err_path___"]#, "one_neutral"]
class TestCase
    def initialize(error_case, error_type, proc)
        @error_case = error_case
        @error_type = error_type
        dir_part = @error_case + "\\" + @error_type[:dir]
        @proc = proc
        @dest = "#{@proc}\\#{dir_part}"
        @flags = "    EXTRA_FLAGS = " + @error_type[:cc_flags] + "\n"
        @cc = "#{@proc}_compile"
        @bench_cc = "#{@proc}_bench_compile"
        @dir = "src\\#{dir_part}"
    end
    def error_case; @error_case; end
    def error_type; @error_type; end
    def dir; @dir; end
    def proc; @proc; end
    def dest; @dest; end
    def flags; @flags; end
    def cc; @cc; end
    def bench_cc; @bench_cc; end
end

def each_case
    ["x86", "x64"].each do |proc|
        FULL_CASE_NAMES.each do |c|
            (TERM_TYPES + ERROR_TYPES).each do |t|
                yield TestCase.new(c, t, proc)
            end
        end
        NO_TERM_CASE_NAME.each do |c|
            ERROR_TYPES.each do |t|
                yield TestCase.new(c, t, proc)
            end
        end
    end
end

def each_bench
    ["x86", "x64"].each do |proc|
        BENCH_CASE_NAMES.each do |c|
            (TERM_TYPES + ERROR_TYPES).each do |t|
                yield TestCase.new(c, t, proc)
            end
        end
    end
end

def prev_case(cur_case)
    last_case = "one_neutral"
    (FULL_CASE_NAMES + NO_TERM_CASE_NAME).each do |c|
        if c == cur_case
            return last_case
        end
        last_case = c
    end
    raise "Missing case #{cur_case}\n"
end

def gen_incr_size_diffs(file, test_case, all_the_sizes)
    return if test_case.error_case == "one_neutral"

    prev_dir = test_case.dest.sub(test_case.error_case, prev_case(test_case.error_case))
    cur_dir = test_case.dest

    all_the_sizes << "#{cur_dir}\\incr_diff.size"
    file.print "build #{cur_dir}\\incr_diff.size: diff_size #{prev_dir}\\main.exe.map | $\n"
    file.print "        #{prev_dir}\\main.exe.asm $\n"
    file.print "        #{cur_dir}\\main.exe.map $\n"
    file.print "        #{cur_dir}\\main.exe.asm $\n"
    file.print "        measure_size.py\n"
    file.print "    DIFF_FILE=#{cur_dir}\\main.exe.map\n"

    if not test_case.error_type[:cc_flags].include? "/EHs"
        all_the_sizes << "#{cur_dir}\\except_incr_diff.size"
        file.print "build #{cur_dir}\\except_incr_diff.size: diff_size #{prev_dir}\\main.exe.map | $\n"
        file.print "        #{prev_dir}\\main.exe.asm $\n"
        file.print "        #{cur_dir}\\main.exe.map $\n"
        file.print "        #{cur_dir}\\main.exe.asm $\n"
        file.print "        measure_size.py\n"
        file.print "    DIFF_FILE=#{cur_dir}\\main.exe.map\n"
        file.print "    FLAGS=--noexcept=True\n"
    end
end

def gen_cmp_retval_size_diffs(file, test_case, all_the_sizes)
    # don't compare to self
    return if test_case.error_type[:dir] == "return_val________"

    retval_dir = test_case.dest.sub(test_case.error_type[:dir], "return_val________")
    cur_dir = test_case.dest

    all_the_sizes << "#{cur_dir}\\retval_diff.size"
    file.print "build #{cur_dir}\\retval_diff.size: diff_size #{retval_dir}\\main.exe.map | $\n"
    file.print "        #{retval_dir}\\main.exe.asm $\n"
    file.print "        #{cur_dir}\\main.exe.map $\n"
    file.print "        #{cur_dir}\\main.exe.asm $\n"
    file.print "        measure_size.py\n"
    file.print "    DIFF_FILE=#{cur_dir}\\main.exe.map\n"
end

def gen_config(file, test_case)
    cc_flags = test_case.flags
    cc = test_case.cc
    dir = test_case.dir
    dest_dir = test_case.dest
    file.print "#===========================================================\n"
    file.print "# #{dest_dir}\n"
    file.print "#===========================================================\n"
    file.print "build #{dest_dir}\\dtor.obj: #{cc} src\\common\\dtor.cpp\n"
    file.print cc_flags
    file.print "build #{dest_dir}\\caller.obj: #{cc} #{dir}\\caller.cpp\n"
    file.print cc_flags
    file.print "build #{dest_dir}\\callee.obj: #{cc} #{dir}\\callee.cpp\n"
    file.print cc_flags
    file.print "build #{dest_dir}\\main.obj: #{cc} #{dir}\\main.cpp\n"
    file.print cc_flags


    file.print "build #{dest_dir}\\main.exe | #{dest_dir}\\main.exe.map: #{test_case.proc}_map_link $\n"
    file.print "    #{dest_dir}\\main.obj $\n"
    file.print "    #{dest_dir}\\caller.obj $\n"
    file.print "    #{dest_dir}\\callee.obj $\n"
    file.print "    #{dest_dir}\\dtor.obj\n\n"

    file.print "build #{dest_dir}\\main.exe.asm: asm_dump #{dest_dir}\\main.exe\n"

    file.print "build #{dest_dir}\\main.size: measure_size #{dest_dir}\\main.exe.map | $\n"
    file.print "    #{dest_dir}\\main.exe.asm $\n"
    file.print "    measure_size.py\n"

    if not test_case.error_type[:cc_flags].include? "/EHs"
        file.print "build #{dest_dir}\\noexcept.main.size: measure_size #{dest_dir}\\main.exe.map | $\n"
        file.print "    #{dest_dir}\\main.exe.asm $\n"
        file.print "    measure_size.py\n"
        file.print "    FLAGS=--noexcept=True\n"
    end
end

def gen_bench(file, test_case)
    cc_flags = test_case.flags
    cc = test_case.bench_cc
    dir = test_case.dir
    dest_dir = test_case.dest
    file.print "#===========================================================\n"
    file.print "# #{dest_dir}\n"
    file.print "#===========================================================\n"
    file.print "build #{dest_dir}\\bench\\TimeLogger.obj: #{cc} src\\common\\TimeLogger.cpp\n"
    file.print cc_flags
    file.print "build #{dest_dir}\\bench\\callee.obj: #{cc} #{dir}\\callee.cpp\n"
    file.print cc_flags

    for nop1 in 0..MAX_NOP_1
        file.print "build #{dest_dir}\\#{nop1}\\bench.obj: #{cc} #{dir}\\bench.cpp\n"
        file.print cc_flags
        file.print "    NOP_COUNTS=/DNOP_COUNT_1=#{nop1} /DNOP_COUNT_2=0\n"
    end
    for nop2 in 0..MAX_NOP_2
        file.print "build #{dest_dir}\\#{nop2}\\dtor.obj: #{cc} src\\common\\dtor.cpp\n"
        file.print cc_flags
        file.print "    NOP_COUNTS=/DNOP_COUNT_1=0 /DNOP_COUNT_2=#{nop2}\n"
        file.print "build #{dest_dir}\\#{nop2}\\caller.obj: #{cc} #{dir}\\caller.cpp\n"
        file.print cc_flags
        file.print "    NOP_COUNTS=/DNOP_COUNT_1=0 /DNOP_COUNT_2=#{nop2}\n"
    end
    for nop1 in 0..MAX_NOP_1
        for nop2 in 0..MAX_NOP_2
            file.print "build #{dest_dir}\\#{nop1}\\#{nop2}\\bench.exe : #{test_case.proc}_bench_link $\n"
            file.print "    #{dest_dir}\\#{nop1}\\bench.obj $\n"
            file.print "    #{dest_dir}\\#{nop2}\\caller.obj $\n"
            file.print "    #{dest_dir}\\bench\\callee.obj $\n"
            file.print "    #{dest_dir}\\#{nop2}\\dtor.obj $\n"
            file.print "    #{dest_dir}\\bench\\TimeLogger.obj\n\n"
        
            file.print "build #{dest_dir}\\#{nop1}\\#{nop2}\\bench.exe.asm: asm_dump #{dest_dir}\\#{nop1}\\#{nop2}\\bench.exe\n"
        end
    end
end

def main()
    File.open("build.ninja", "w") do |h|
        h.print "ninja_required_version = 1.7\n\n"
        h.print "include windows.ninja\n\n"

        all_the_sizes = []
        each_case do |c|
            gen_config(h, c)
            gen_cmp_retval_size_diffs(h, c, all_the_sizes)
            gen_incr_size_diffs(h, c, all_the_sizes)
        end

        each_bench do |c|
            gen_bench(h, c)
        end

        h.print "build totals\\sizes.csv: collect_sizes"
        each_case do |c|
            h.print " #{c.dest}\\main.size"
            if not c.error_type[:cc_flags].include? "/EHs"
                h.print " #{c.dest}\\noexcept.main.size"
            end
        end
        h.print " | concat_files.py\n\n"

        h.print "build totals\\times.csv: collect_benches $\n"
        each_bench do |c|
            for nop1 in 0..MAX_NOP_1
                for nop2 in 0..MAX_NOP_2
                    h.print "    #{c.dest}\\#{nop1}\\#{nop2}\\bench.exe $\n"
                end
            end
        end
        h.print "\n\n"

        h.print "build bench: phony $\n"
        h.print "    totals\\times.csv $\n"
        each_bench do |c|
            for nop1 in 0..MAX_NOP_1
                for nop2 in 0..MAX_NOP_2
                    h.print "    #{c.dest}\\#{nop1}\\#{nop2}\\bench.exe.asm $\n"
                end
            end
        end
        h.print "\n\n"

        h.print "default totals\\sizes.csv $\n"
        all_the_sizes.each do |s|
            h.print "    #{s} $\n"
        end
        h.print "\n"
    end
end

if __FILE__ == $0
   main()
end
