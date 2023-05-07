from flask import Flask, request, render_template

app = Flask(__name__)

@app.route('/')
def index():
  return render_template('index.html')

@app.route('/upload', methods=['POST'])
def upload():
    file = request.files['file']
    file.save(file.filename)
    return 'File uploaded successfully'

if __name__ == '__main__':
    app.run()