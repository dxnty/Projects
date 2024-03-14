#This program is only a little part of a bigger project (still not public) --- Clearly is not finished :)

import csv
import requests
from bs4 import BeautifulSoup

# [] Functions []

def main():
    print("Hello, I'm the main function of the Scraper file.\nIf you see me something is wrong. Run again")


# Receive a website URL and an HTML tag to look for and return the list with the desired informations
def base_scraper(URL, HTML_TAG_condition):
    website_url = URL
    SERVERresponse = requests.get(website_url) #HTML code response received from the server (es. 200, 404, 301 etc.)
    HTML_content = SERVERresponse.content #HTML webpage content (HTML tags, paragraph etc.)
    soup = BeautifulSoup(HTML_content, 'html.parser')

    return soup.find_all(HTML_TAG_condition)


# Receive a dirty list. Cleans it and write it into a consistent csv dataset 
def dataset_creator(list):
    print(list)
    #fetch and catalog the list received and fix the CSV syntax so that it's possible to correctly upload it into a csv dataset


# [] Main function calls []
if __name__ == "__main__":
    titles = base_scraper("https://pypi.org/project/beautifulsoup4/","p")
    dataset_creator(titles)