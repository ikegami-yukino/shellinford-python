use ExtUtils::MakeMaker;
WriteMakefile(
  NAME         => 'Shellinford',
  VERSION_FROM => 'lib/Shellinford.pm',
  LIBS         => ['-L/usr/lib -L/usr/local/lib -lshellinford'],
  INC          => '-I. -I/usr/include',
  CC           => '/usr/bin/g++ -O2',
  LD           => '/usr/bin/g++ -O2',
  XSOPT        => '-C++',
  TYPEMAPS     => ['perlobject.map' ],
);

