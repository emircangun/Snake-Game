# TODO:
# validation ekle
#
#


import json
from werkzeug.security import generate_password_hash

class UserSchema():
    def __init__(self, username, hashed_password, games):
        self.username = username
        self.password = hashed_password
        self.games = games

    def user_to_json(self):
        response = {
            "username": self.username,
            "password": self.password,
            "games": self.games
        }

        return json.dumps(response)