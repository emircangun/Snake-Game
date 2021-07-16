# TODO:
# validation ekle
#
#


class UserSchema():
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