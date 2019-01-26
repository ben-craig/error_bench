TEST_DIRS = [
    {:dir => "wont_throw", :config => "no_eh"},
    {:dir => "may_throw", :config => "eh"},
]

def gen_config(file, test_config, proc)
    dir = test_config[:dir]
    config = test_config[:config]
    cc = "#{proc}_#{config}_compile"
    file.print "#===========================================================\n"
    file.print "# #{proc}\\#{dir}\n"
    file.print "#===========================================================\n"
    file.print "build #{proc}\\#{dir}\\dtor.obj: #{cc} common\\dtor.cpp\n"
    file.print "build #{proc}\\#{dir}\\caller.obj: #{cc} #{dir}\\caller.cpp\n"
    file.print "build #{proc}\\#{dir}\\callee.obj: #{cc} #{dir}\\callee.cpp\n"
    file.print "build #{proc}\\#{dir}\\bench.obj: #{cc} #{dir}\\bench.cpp\n"
    file.print "build #{proc}\\#{dir}\\main.obj: #{cc} #{dir}\\main.cpp\n\n"


    file.print "build #{proc}\\#{dir}\\main.exe | #{proc}\\#{dir}\\main.exe.map: #{proc}_map_link $\n"
    file.print "    #{proc}\\#{dir}\\main.obj $\n"
    file.print "    #{proc}\\#{dir}\\caller.obj $\n"
    file.print "    #{proc}\\#{dir}\\callee.obj $\n"
    file.print "    #{proc}\\#{dir}\\dtor.obj\n\n"

    file.print "build #{proc}\\#{dir}\\main.size: measure #{proc}\\#{dir}\\main.exe.map\n\n"

    file.print "build #{proc}\\#{dir}\\bench.exe : #{proc}_link $\n"
    file.print "    #{proc}\\#{dir}\\bench.obj $\n"
    file.print "    #{proc}\\#{dir}\\caller.obj $\n"
    file.print "    #{proc}\\#{dir}\\callee.obj $\n"
    file.print "    #{proc}\\#{dir}\\dtor.obj\n\n"
end

def main()
    File.open("generated_targets_from_gen.rb.ninja", "w") do |h|
        h.print "ninja_required_version = 1.7\n\n"
        TEST_DIRS.each do |t|
            ["x86", "x64"].each do |proc|
                gen_config(h, t, proc)
            end
        end

        h.print "default"
        TEST_DIRS.each do |t|
            ["x86", "x64"].each do |proc|
                h.print " #{proc}\\#{t[:dir]}\\bench.exe"
                h.print " #{proc}\\#{t[:dir]}\\main.size"
            end
        end
        h.print "\n"
    end
end

if __FILE__ == $0
   main()
end
