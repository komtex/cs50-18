import cs50
import csv
import os

from flask import Flask, jsonify, redirect, render_template, request

# Configure application
app = Flask(__name__)

# Reload templates when they are changed
app.config["TEMPLATES_AUTO_RELOAD"] = True


@app.after_request
def after_request(response):
    """Disable caching"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/", methods=["GET"])
def get_index():
    return redirect("/form")


@app.route("/form", methods=["GET"])
def get_form():
    return render_template("form.html")

@app.route("/form", methods=["POST"])
def post_form():
    if not request.form.get("name") or not request.form.get("group") or not request.form.get("phone"):
        return render_template("error.html", message = "You must fill input field")
    with open("survey.csv", "a") as file:
        writer = csv.DictWriter(file, fieldnames = ["name", "phone", "group", "k1", "k2"])
        writer.writerow({"name": request.form.get("name"), "phone": request.form.get("phone"), "group": request.form.get("group"), "k1": request.form.get("k1"), "k2": request.form.get("k2")})
    return redirect("/sheet")

@app.route("/sheet", methods=["GET"])
def get_sheet():
    with open('survey.csv', 'r') as file:
        reader = csv.reader(file)
        table_rows = list(reader)

    return render_template("sheet.html", table_rows=table_rows)
