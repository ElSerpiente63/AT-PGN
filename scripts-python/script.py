import couchdb
import json
import requests


import pkg_resources

# Récupérer la liste de tous les packages installés
packages = [dist.project_name for dist in pkg_resources.working_set]

# Afficher chaque package avec sa version
for package in packages:
    version = pkg_resources.get_distribution(package).version
    print(f"{package} ({version})")