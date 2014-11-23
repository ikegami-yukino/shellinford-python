from . import shellinford

VERSION = (0, 3, 1)
__version__ = '0.3.1'
__all__ = ['FMIndex', 'bit_vector', 'bwt']

FMIndex = shellinford.FMIndex
bit_vector = shellinford.bit_vector
bwt = shellinford.bwt
