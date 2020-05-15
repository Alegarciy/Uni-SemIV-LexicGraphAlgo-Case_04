import os
import json
import re

#Python programs to work with human language data
import nltk
#Python library for pulling data out of HTML and XML files
from bs4 import BeautifulSoup

class HtmlManager(object):
    def __init__(self):
        self.filename = "Documento90.html"
        self.destinyFilename = "sustantivos.json"
        self.textdata = {}
        #Beautiful soup object
        self.html = None
        #NLTK tag for representinf nouns
        self.targetTags = ["NN", "NNS"]

    def readHtml(self):
        with open(self.filename, encoding="utf-8") as file:
            #Running the "Documento90.html" through Beautiful soup gives us a nested data structure
            self.html = BeautifulSoup(file.read(), "html.parser")

    def readText(self):
        paragraphCounter = 1
        #Find all the tags that have <p> && where id = U90 -> Finds all the paragraphs
        paragraphs = self.html.find_all("p", {"id": re.compile(r'U90')})

        for paragraph in paragraphs:
            text = paragraph.getText()
            #text = re.sub(r'\w*\d\w*', '', text).strip()
            #text = text.lower()

            #Array of strings representing words
            words = nltk.word_tokenize(text)
            #Tags the type of word it is -> NN:noun, it retuns [word, tag]
            taggedWords = nltk.pos_tag(words)
            print(taggedWords)
            #Empty target words
            targetWords = []
            for word in taggedWords:
                tag = word[1]
                #Check if word is a noun, then append to targetWords
                if tag in self.targetTags and len(word[0]) > 3:
                    targetWords.append(word[0])

            self.textdata[paragraphCounter] = targetWords
            paragraphCounter += 1

    def writeTextData(self):
        with open(self.destinyFilename, "w", encoding="utf-8") as file:
            json.dump(self.textdata, file, ensure_ascii=False)

    def readTextData(self):
        with open(self.destinyFilename, encoding="utf-8") as file:
            data = json.load(file)
        json.dumps(data)
        return data

#Create Object
manager = HtmlManager()
#Get the paragraphs from the html file
manager.readHtml()
#Get the nouns and store them in textdata
manager.readText()
#Convert the textdata into a json file
manager.writeTextData()