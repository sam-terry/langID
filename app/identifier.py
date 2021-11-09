import os
import math

print("\n\nLanguage Identifier v0.0.1")
print("Use 'exit()' to quit\n\n")

langs = ['Dutch','German','Swedish','French','Spanish','Italian','Turkish']
corpora = {}
counts = {}
model = {}

# Generate the absolute path to the pwd
currentWD = os.path.dirname(os.path.realpath(__file__))
for lang in langs:

    # Interpolate the language name into the relative path for the corpus files; combine with absolute path
    absPath = os.path.join(currentWD, "corpora/Monolingual_data/%s.txt" %lang)

    with open(absPath, 'r') as corpFile:
    	corpora[lang] = corpFile.read()

    counts[lang] = {}
    model[lang] = {}



# Count all trigrams across the corpora and store counts for each language 
progress = 0
for lang in langs:
    print("Training models...(%s/7)\n" % str(progress))
    for i in range( len(corpora[lang]) - 2):
        threeGram = corpora[lang][i:i+3]
        
        # If the model for a language does not yet have a value for the trigram, initialize it to 0
        for l in langs:
            if threeGram not in counts[l]:
                counts[l][threeGram] = 0
        
        # Increment trigram count for the language in which we encountered it
        counts[lang][threeGram] += 1
    
    # Calculate log probabilities of each trigram 
    for gram in counts[lang]:
        if counts[lang][gram] > 0:
            model[lang][gram] = math.log(counts[lang][gram] / float(len(corpora[lang]) - 2))
    progress += 1
print("Training models...(%s/7)\n\n" % str(progress))
print("Done!\n\n")



# Main loop for excepting queries
utterance = input("Please enter a string: ")
while utterance != "exit()":

    # Break the string into trigrams
    uttGrams = []
    for j in range(len(utterance) - 2):
        uttGrams.append(utterance[j:j+3])


    best_guess = langs[0]
    best_score = 0
    current_score = 0

    # For each language, if the trigram exists in the model
    for lang in langs:
        for gram in uttGrams:
            if gram in model[lang]:
                current_score += model[lang][gram] # Increase the score for the current language by the log probability for that trigram in said language

            # If at any point the language's score becomes the top score, it is now the best guess
            if current_score >= best_score:
                best_score = current_score
                best_guess = lang

        current_score = 0        
        
    print("This string is most likely in %s" % (best_guess))
    print("\n")

    utterance = input("Please enter a string: ")
