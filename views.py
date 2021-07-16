'''
    login
    sign_up
    
    get_game
    add_game
'''

#  burada password hash et, api arası hash olmayan password geçişi sağlıklı mıdır?

from flask import current_app, request
from werkzeug.security import generate_password_hash, check_password_hash

# existing user
def login():
    '''
        {
            "username": ...,
            "password": ...
        }
    '''
    request_data = request.get_json()
    username = request_data.get("username")
    password = request_data.get("password")
    db = current_app.config.get("db")
    if db.check_user(username, password):
        return "Succeed"
    return "Failed"


# new user
def signup():
    '''
        {
            "username": ...,
            "password": ...
        }
    '''
    request_data = request.get_json()
    username = request_data.get("username")
    password = request_data.get("password")
    db = current_app.config.get("db")
    if username and password:
        if db.get_user(username) is None:
            hashed_password = generate_password_hash(password)
            db.add_user(username, hashed_password)
            return "Succeed"
        return "Existing user"
    return "Failed"

# /api/users/<string:username>/add_game
def add_game(username):
    '''
        {
            "password": ...,
            "score": ...,
            "direction_history": ...
        }
    '''
    request_data = request.get_json()
    password = request_data.get("password")
    score = request_data.get("score")
    direction_history = request_data.get("direction_history")
    db = current_app.config.get("db")
    if db.check_user(username, password):
        db.add_game(username, score, direction_history)
        return "Succeed"
    return "Failed"

# /api/users/<string:username>/games/<int:game_id>
def get_game(username, game_id):
    db = current_app.config.get("db")
    user = db.get_user(username)
    if user is not None:
        games = user.get("games")
        game = games[game_id]
        return game
    return "Failed"


