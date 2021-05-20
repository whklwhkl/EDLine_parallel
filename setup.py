from distutils.core import setup
from glob import glob


setup (name = 'edline',
       version = '0.1',
       author = 'zhemu',
       description = '''line detection```
       ''',
       py_modules = ['edline'],
       packages=[''],
       package_data={'': glob('edline.*.so')},
       )
