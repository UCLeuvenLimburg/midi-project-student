require 'find'


Find.find('docs') do |entry|
    if entry.end_with? '.asciidoc'
        puts "Processing #{entry}"

        contents = File.open(entry, :encoding => 'utf-8') do |f|
            f.read
        end

        contents.gsub!(%r{\A.*?=}m, '=')
        contents = <<~END + contents
        :tip-caption: 💡
        :note-caption: ℹ️
        :important-caption: ⚠️
        :task-caption: 👨‍🔧
        :source-highlighter: rouge
        :toc: left
        :toclevels: 3
        :experimental:
        :nofooter:
        END

        IO.write(entry, contents)
    end
end
