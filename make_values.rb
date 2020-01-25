def uniq_values(size,seed)
  rng = Random.new(seed)
  h={}
  while( h.size<size )
    h[rng.rand(1<<30)]=true
  end
  return h.keys
end

[ 2, 20, 200, 2000 ].each do |size|
  values = uniq_values(size,0)
  keys = uniq_values(size,1)
  File.open( "values_#{size}.hxx", "w" ) do |f|
    keys.zip(values).each do |k,v|
      f.puts( "KEY_VALUE(#{k}, #{v})" )
    end
  end
end
