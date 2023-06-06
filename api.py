import fastapi 
from fastapi import FastAPI 
import pydantic
from pydantic import BaseModel
import typing
import uvicorn
from typing import Optional
import couchdb
import json
import requests
import sys
import passlib
import importlib.util
module_spec = importlib.util.spec_from_file_location('config', 'C:/Users/33769/Desktop/config/config.py')
module = importlib.util.module_from_spec(module_spec)
module_spec.loader.exec_module(module)
app = FastAPI()


class Distance(BaseModel):
    distance: int
    token: str
    hour: Optional[str]

@app.post('/distance/recorder/db')
async def save_distance(distance: Distance):
    database = couchdb.Database(f'http://{module.username}:{module.password}@127.0.0.1:5984/atpgn')
    url_verify = f"http://{module.username}:{module.password}@127.0.0.1:5984/atpgn/_design/login/_view/login?key='{token}'"
    response = requests.get(url_verify)
    payload = {
        "distance":distance['distance'],
        "hour":distance['hour']
    }
    if distance['token'] == response.json()['rows'][0]['value']:
        database.save(payload)
    else:
        return {"Status":'not done'}

if __name__ == '__main__':
    uvicorn.run(host='127.0.0.1', port=2000)

