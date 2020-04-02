require 'find'


Find.find('docs') do |entry|
    if entry.end_with? '.asciidoc'
        puts "Processing #{entry}"

        contents = File.open(entry, :encoding => 'utf-8') do |f|
            f.read
        end

        contents.gsub!(%r{link:([^#\[]*)#?(.*?)\[(.*?)\]}, '<<\1#\2,\3>>')

        IO.write(entry, contents)
    end
end
