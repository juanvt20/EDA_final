import os
import time
import spacy # Libreria de nlp
from collections import Counter # Para contar palabras rápidamente
import matplotlib.pyplot as plt
from wordcloud import WordCloud 

import eda_cpp # Programa de c++

# Variables modificables
K = 8                # Notias procesadas
WORDS_WORDCLOUD = 20 # Palabras de la wordcloud
TXTS = "./AP_BBC_CNN_Reuters_nosource_nodate_novo_nofull" # Carpeta con los .txt

# Modelo nlp
print("Cargando modelo NLP...")

nlp = spacy.load("en_core_web_sm", disable=["parser", "ner"])

def process_text_nlp(text):

    #Tokeniza, limpia, lematiza y filtra sustantivos.

    doc = nlp(text.lower()) # Vuelve todo minuscula y lo tokeniza
    
    valid_words = [] # Almacenar palabras
    for token in doc:

        if not token.is_stop and token.is_alpha and token.pos_ in ['NOUN', 'PROPN']: # Elimina articulos o preposiciones, elimina simbolos y numeros y toma sustantivos y nombres
            valid_words.append(token.lemma_) # Lematizacion 
            
    return valid_words

def main():
   
    manager = eda_cpp.TopicManager(K)  # crea el objeto de la clase C++
    
    # Configuracion de visualizacion
    plt.ion() # Actualizacion en vivo
    fig, ax = plt.subplots(figsize=(10, 6))

    files = sorted([f for f in os.listdir(TXTS) if f.endswith('.txt')])
    
    print(f"Iniciando procesamiento de {len(files)} noticias con K={K}...")

    for i, filename in enumerate(files):
        filepath = os.path.join(TXTS, filename)
        
        # Lectura
        with open(filepath, 'r', encoding='utf-8') as f:
            content = f.read()#lo pone en un string
            
        # NLP
        nouns = process_text_nlp(content)
        
        # Contamos frecuencias locales en Python para pasarlas limpias a c++
        local_counts = Counter(nouns)
        words_vec = list(local_counts.keys())
        counts_vec = list(local_counts.values())
        
        # Procesamiento en c++
        print(f"Iniciando almacenamiento de K={i+1}")
        manager.process_news(words_vec, counts_vec)
        
        # Obtener datos de c++
        print(f"Iniciando consulta de K={i+1}")
        freq_dict = manager.get_general_table()

        # Visualización
        if len(freq_dict) > 0:
            wc = WordCloud(width=800, height=400, background_color='white', max_words=WORDS_WORDCLOUD)
            wc.generate_from_frequencies(freq_dict)
            
            ax.clear()
            ax.imshow(wc, interpolation='bilinear')
            ax.axis("off")
            ax.set_title(f"Trending Topics (K: {K} | Noticia: {i+1}/{len(files)})")
            plt.pause(2) # Pausa para actualizar el grafico
            #time.sleep(2)

    plt.ioff()
    plt.show()

if __name__ == "__main__":
    main()
