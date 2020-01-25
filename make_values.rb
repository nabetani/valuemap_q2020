def uniq_values(size,seed)
  rng = Random.new(seed)
  h={}
  while( h.size<size )
    h[rng.rand(1<<30)]=true
  end
  return h.keys
end

SIZES = [ 3, 10, 30, 100, 300 ]


File.open( "values.hxx", "w" ) do |f|
  SIZES.each do |size|
    values = uniq_values(size,0)
    f.puts( "#define KEY_VALUES_#{size} \\" )
    keys = uniq_values(size,1)
    keys.zip(values).each do |k,v|
      f.puts( "KEY_VALUE(#{k}, #{v}) \\" )
    end
    f.puts("")
    f.puts("")
  end
end
