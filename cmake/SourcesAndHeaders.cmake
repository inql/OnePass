file(GLOB sources
  src/*.cpp
)

set(exe_sources
		${sources}
)

file(GLOB headers
  include/*.hpp
)

file(GLOB test_sources
  test/src/*.cpp
)
