import os
import http.cookies as cookies
from utils import Session
import json

cookie=cookies.SimpleCookie(os.environ["HTTP_COOKIE"])
session=Session(cookie)
session.destroy()
del cookie['SESSION_ID']
Session(cookie)

print('Content-Type:text/html') # ili print('Content-Type:application/json')
print(cookie.output())
print()

# ...
