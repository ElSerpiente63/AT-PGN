import fastapi 
from fastapi import FastAPI 
import pydantic
from pydantic import BaseModel
import typing
import couchdb
import json
import requests
import sys
import importlib.util
module_spec = importlib.util.spec_from_file_location('config', 'C:/Users/33769/Desktop/config/config.py')
module = importlib.util.module_from_spec(module_spec)
module_spec.loader.exec_module(module)
app = FastAPI()


class Distance(BaseModel):
    distance: int
    token: str

@app.post('/distance/recorder/db')
async def save_distance(distance: Distance):
    url_verify = f'http://{module.username}:{module.password}@127.0.0.1:5984/'