# spellchecker.py
from spellchecker import SpellChecker

def correct_text(text):
    spell = SpellChecker()
    words = text.split()
    corrected_words = []

    for word in words:
        corrected_word = spell.correction(word)
        corrected_words.append(corrected_word if corrected_word else word)

    return " ".join(corrected_words)


if __name__ == "__main__":
    sample = input("Enter text to check spelling: ")
    print("Corrected text:", correct_text(sample))
