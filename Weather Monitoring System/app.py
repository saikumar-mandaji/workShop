from flask import Flask,render_template,request

usr = "iot"
pwd ="12345"
t = 0
h = 0

app = Flask(__name__)
@app.route('/',methods=["get","post"])
def home():
    if request.method=="GET":
        return render_template('home.html')
    if request.method=="POST":
            return ""
      
@app.route('/signin',methods=["get","post"])
def signin():
    if request.method=="GET":
        return render_template('signin.html')
    if request.method=="POST":
        user,pw = request.data.decode("utf-8").split(",")
        print(user,pw)
        if user == usr and pw == pwd:return {"data":1}
        else:return {"data":0}

@app.route('/main',methods=["get","post"])
def main():
    if request.method=="GET":
        return render_template('dashBoard.html',name = usr)
    if request.method=="POST":
        data= request.data.decode("utf-8")
        print(data)
        return {'T': t, 'H': h}
@app.route("/update",methods=["get","post"])
def update():
    global t
    global h
    t = request.args.get('T')
    h = request.args.get('H')
    return "OK"



if __name__ == '__main__':  
    app.run(host = '0.0.0.0', port= 8080,debug= True)