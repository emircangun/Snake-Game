from pymongo import MongoClient
from flask import current_app
from schemas import UserSchema, GameSchema
from werkzeug.security import check_password_hash
import json

class Database():
    '''
        get_user(username)
        add_user(user)
    '''
    def __init__(self):
        client = MongoClient(current_app.config.get("DATABASE_URI"))
        self.db = client["snake-database"]
        self.user_collection = self.db["users"]

    def get_user(self, username):
        query = { "username": username }
        user = self.user_collection.find_one(query)
        return user

    def add_user(self, username, hashed_password):
        user = UserSchema(username, hashed_password, games=[])
        user_json = user.user_to_json()
        self.user_collection.insert_one(user_json)

    def add_game(self, username, score, direction_history):
        query = { "username": username }
        user = self.user_collection.find_one(query)
        games = user.get("games")
        game = GameSchema(score, direction_history)
        game_json = game.game_to_json()
        games.append(game_json)
        self.user_collection.update_one({ "username": username}, { "$set": { "games": games } })

    def check_user(self, username, password):
        user = self.get_user(username)
        if user is not None:
            if password:
                if check_password_hash(user.get("password"), password):
                    return True
        return False


class TestDatabase(Database):
    def test_fetch_data(self):
        users = self.user_collection.find()
        response = []
        for user in users:
            user["_id"] = str(user["_id"])
            response.append(user)
        return json.dumps(response)

    def test_get_user(self):
        return self.get_user("sdfa")

    def test_add_user(self):
        self.add_user("test2", "test2")

    def test_add_game_to_user(self):
        self.add_game("test3", [2, 1, 0, 3])


if __name__ == "__main__":
    db = TestDatabase()
    # print(db.test_fetch_data())
    # print(db.test_get_user())
    # db.test_add_user()
    db.test_add_game_to_user()



