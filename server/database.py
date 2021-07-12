from types import resolve_bases
from pymongo import MongoClient
from flask import current_app
import json

class Database():
    '''
        get_user(username)
        add_user(user)
    '''
    def __init__(self):
        # client = MongoClient(current_app.config["DATABASE_URI"])
        client = MongoClient("mongodb+srv://emircangun:PdLym640NLg0jI7S@snake-database.gd2rk.mongodb.net/snake-database?retryWrites=true&w=majority")
        self.db = client["snake-database"]
        self.user_collection = self.db["users"]










class TestDatabase(Database):
    def test_fetch_data(self):
        users = self.user_collection.find()
        response = []
        for user in users:
            user["_id"] = str(user["_id"])
            response.append(user)
        return json.dumps(response)


if __name__ == "__main__":
    db = TestDatabase()
    print(db.test_fetch_data())




