from flask import Flask,render_template,request


alc = 0

th = 400

bt=1

app = Flask(__name__)
@app.route('/',methods=["get","post"])
def home():
    global alc
    global th
    if request.method=="GET":
        return render_template('home.html')
    if request.method=="POST":
            if float(alc) > float(th):
                st=0
            else:
                st = 1  
            return {"data":{"Vstatus":st,"alc":alc}}
                 
@app.route('/st',methods=["get","post"])
def sts():
     global bt
     if request.method=="POST":
          bt = int(request.data.decode("utf-8").split(":")[1])
          print(bt)
     return "OK"
     

@app.route("/update",methods=["get","post"])
def update():
    global alc
    global bt
    alc = request.args.get('A')
    print(alc)
    return str(bt)



if __name__ == '__main__':  
    app.run(host = '0.0.0.0', port= 8080,debug= True)