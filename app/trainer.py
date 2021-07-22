import csv
import os

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

    # Remove all model specifications to be replaced by this build
    os.remove(os.path.join(currentWD, "models/mod_%s.csv" %lang))

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
    
    # Calculate scores by dividing each trigram count by the total trigrams in each corpus
    for gram in counts[lang]:
        if counts[lang][gram] > 0:
            model[lang][gram] = counts[lang][gram] / float(len(corpora[lang]) - 2)

    progress += 1
print("Training models...(%s/7)\n\n" % str(progress))
print("Done!\n\n")


print("Writing model specifications...\n\n")
for l in langs:
    writePath = os.path.join(currentWD, "models/mod_%s.csv" %l)
    with open(writePath, 'w') as outfile:
        scorewriter = csv.writer(outfile)
        for g in model[l]:
            scorewriter.writerow([g,model[l][g]])
    
print("Done!")