import couchdb
import requests
import json
import importlib.util
module_spec = importlib.util.spec_from_file_location('config', 'C:/Users/33769/Desktop/config/config.py')
module = importlib.util.module_from_spec(module_spec)
module_spec.loader.exec_module(module)
json = {"token":"45e04c0f-07d8-48ab-9386-b0af81bab9c3"}
response = requests.post(f'http://{module.username}:{module.password}@127.0.0.1:5984/atpgn', json=json)
if response:
    print("Request sent")
    print(response.status_code)
else:
    print("Request failed")

token = json['token']
url = f'http://{module.username}:{module.password}@127.0.0.1:5984/atpgn/_design/login/_view/login?key="{token}"'
print(url)
res = requests.get(url)
print(res.json()['rows'][0]['value'])