# TODO:
# validation ekle
#
#


class UserSchema:
    def __init__(self, username, hashed_password, games):
        self.username = username
        self.password = hashed_password
        self.games = games

    def user_to_json(self):
        user_json = {
            "username": self.username,
            "password": self.password,
            "games": self.games
        }

        return user_json

class GameSchema:
    def __init__(self, score, direction_history):
        self.score = score
        self.direction_history = direction_history

    def game_to_json(self):
        game_json = {
            "score": self.score,
            "direction_history": self.direction_history
        }

        return game_json