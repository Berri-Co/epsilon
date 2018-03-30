from jinja2 import nodes
from jinja2.ext import Extension

def camel(s):
    parts = s.split('_')
    return ''.join([p.title() for p in parts])

def lowerfirst(s):
    return s[0].lower() + s[1:]

class Jinja2Extension(Extension):
    def __init__(self, environment):
        super().__init__(environment)
        environment.filters['camel'] = camel
        environment.filters['lowerfirst'] = lowerfirst
