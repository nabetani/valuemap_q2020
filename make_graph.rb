# frozen_string_literal: true

require 'charma'

def parse(o)
  r = o.split(/[\r\n]+/).map{ |line|
    m = /^\s*([\w_]+)\:\s+(\d+)\s*tick\=\s*([\d\.]+)/.match(line)
    if m
      { name:$1, size:$2.to_i, tick:$3.to_f }
    else
      nil
    end
  }.compact
  names = r.map{ |e| e[:name] }.uniq
  seri = names.map{ |name|
    ticks = r.select{ |e| e[:name]==name }.sort_by{ |e| e[:size] }.map{ |e| e[:tick] }
    { name:name, y:ticks }
  }
  x_ticks = r.map{ |e| e[:size] }.sort.uniq.map(&:to_s)
  [ x_ticks, seri ]
end

def make_opts(cc, o)
  x_ticks, seri = parse(o)
  {
    y_scale: :log10,
    y_range: [1e-3, 1],
    title:cc,
    x_ticks: x_ticks,
    series: seri,
  }
end

Charma::Document.new do |doc|
  %w( clang gcc ).each do |cc|
    opts = make_opts(cc, %x( "bin/out_#{cc}" ))
    doc.new_page do |page|
      page.add_linechart( opts )
    end
  end
  doc.render( "graph.pdf" )
end
