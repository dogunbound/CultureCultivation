rm -rf release
rm -rf debug

mkdir release
mkdir release/assets
mkdir debug
mkdir debug/assets
cp -r src/assets/* release/assets
cp -r src/assets/* debug/assets/
