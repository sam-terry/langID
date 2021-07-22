import os


langs = ['Dutch','German','Swedish','French']
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


for lang in langs:

    for i in range( len(corpora[lang]) - 2):
        threeGram = corpora[lang][i:i+3]
        
        for l in langs:
            if threeGram not in counts[l]:
                counts[l][threeGram] = 0
        
        counts[lang][threeGram] += 1
    
    for gram in counts[lang]:
        model[lang][gram] = counts[lang][gram] / float(len(corpora[lang]) - 2)

utterance = raw_input("Please enter a string: ")

uttGrams = []
for j in range(len(utterance) - 2):
    uttGrams.append(utterance[j:j+3])


best_guess = langs[0]
best_score = 0
current_score = 0

for lang in langs:
    for gram in uttGrams:
        if gram in model[lang]:
            current_score += model[lang][gram]

    if current_score >= best_score:
        best_score = current_score
        best_guess = lang
    # print(current_score)
    current_score = 0        
# print(current_score)
# print("\n")
print("The probability of this string occuring in %s is %s" % (best_guess, str(round(best_score, 2))))
