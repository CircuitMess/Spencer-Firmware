#!/bin/bash

set -e -o pipefail

# Takes the input file sentences.txt and saves .mp3 files in the data folder

# Google TTS api key
KEY=

while IFS= read -r sentence; do
  dir=$(echo "$sentence" | cut -d " " -f1)
  name=$(echo "$sentence" | cut -d " " -f2)
  sentence=$(echo "$sentence" | tail -c +$(expr ${#dir} + ${#name} + 3))
  mkdir -p "data/$dir"
  echo "$dir/$name: $sentence"
  curl -s --location --request POST "https://texttospeech.googleapis.com/v1/text:synthesize?key=$KEY" \
    --header "Content-Type: application/json" \
    --data-raw '{
    "input": { "text": "'"$sentence"'" },
    "voice": {
        "languageCode": "en-US",
        "name": "en-US-Standard-D",
        "ssmlGender": "NEUTRAL"
    },
    "audioConfig": {
        "audioEncoding": "MP3",
        "speakingRate": 0.96,
        "pitch": 7.2,
        "sampleRateHertz": 16000
    }
  }' | jq -r '.audioContent' | base64 -d  | ffmpeg -loglevel quiet -f mp3 -i pipe: -c:a libmp3lame -b:a 24k "data/$dir/$name.mp3"
done < sentences.txt
