const puppeteer = require('puppeteer');
const fs = require('fs');
const path = require('path');
const axios = require('axios');
const sharp = require('sharp');

async function convertImageToPng(inputPath, outputPath) {
    try {
        await sharp(inputPath)
            .png()
            .toFile(outputPath);
    } catch (error) {
        console.error(`Error converting ${inputPath} to ${outputPath}:`, error);
        throw error; // Re-throw the error to be caught in the Promise.all
    }
}

async function downloadImage(url, filepath) {
    const writer = fs.createWriteStream(filepath);
    const response = await axios({
        url,
        method: 'GET',
        responseType: 'stream'
    });
    response.data.pipe(writer);
    return new Promise((resolve, reject) => {
        writer.on('finish', resolve);
        writer.on('error', reject);
    });
}

async function parseWebsite(url) {
    const browser = await puppeteer.launch();
    const page = await browser.newPage();
    await page.goto(url, { waitUntil: 'networkidle2' });

    const data = await page.evaluate(() => {
        function formatCardID(cardID) {
            // Remove spaces and ensure the card number is zero-padded to three digits if necessary
            return cardID.replace(/(\w+)\s*#(\d+)/, (match, p1, p2) => `${p1}#${p2.padStart(3, '0')}`);
        }

        const typeMapping = {
            'G': 'GRASS',
            'W': 'WATER',
            'R': 'FIRE',
            'L': 'LIGHTNING',
            'P': 'PSYCHIC',
            'F': 'FIGHTING',
            'D': 'DARKNESS',
            'M': 'METAL',
            'C': 'COLORLESS'
        };

        const cards = [];
        const imageUrls = [];
        const cardElements = document.querySelectorAll('.card-classic');

        cardElements.forEach(cardElement => {
            const cardIDElement = cardElement.querySelector('.card-set-info');
            const nameElement = cardElement.querySelector('.card-text-name a');
            const typeElement = cardElement.querySelector('.card-text-type');
            const hpElement = cardElement.querySelector('.card-text-title');
            const weaknessElement = cardElement.querySelector('.card-text-wrr');
            const retreatCostElement = cardElement.querySelector('.card-text-wrr');
            const imageElement = cardElement.querySelector('.image img');

            if (!cardIDElement || !nameElement || !typeElement || !hpElement || !weaknessElement || !retreatCostElement || !imageElement) {
                return; // Skip this card if any required element is missing
            }

            const cardID = formatCardID(cardIDElement.innerText.trim());
            const name = nameElement.innerText.trim();
            const typeMatch = hpElement.innerText.match(/-\s*(\w+)\s*-/);
            const hpMatch = hpElement.innerText.match(/(\d+) HP/);
            const weaknessMatch = weaknessElement.innerText.match(/Weakness: (\w+)/);
            const retreatCostMatch = retreatCostElement.innerText.match(/Retreat: (\d+)/);

            if (!typeMatch || !hpMatch || !weaknessMatch || !retreatCostMatch) {
                return; // Skip this card if any required data is missing
            }

            const type = typeMatch[1].toUpperCase();
            const hp = parseInt(hpMatch[1], 10);
            const weakness = weaknessMatch[1].toUpperCase();
            const retreatCost = Array(parseInt(retreatCostMatch[1], 10)).fill("COLORLESS");
            const isEx = name.toLowerCase().includes('ex');
            const moves = [];
            const imageUrl = imageElement.getAttribute('src');
            imageUrls.push({ cardID, imageUrl });

            const moveElements = cardElement.querySelectorAll('.card-text-attack');
            moveElements.forEach(moveElement => {
                const moveInfoElement = moveElement.querySelector('.card-text-attack-info');
                const moveCostElement = moveElement.querySelector('.ptcg-symbol');

                if (!moveInfoElement || !moveCostElement) {
                    return; // Skip this move if any required element is missing
                }

                const moveName = moveInfoElement.innerText.split(' ').slice(1).join(' ').replace(/\d+$/, '').trim();
                const movePowerMatch = moveInfoElement.innerText.match(/(\d+)$/);

                if (!movePowerMatch) {
                    return; // Skip this move if power is missing
                }

                const movePower = parseInt(movePowerMatch[1], 10);
                const moveCost = moveCostElement.innerText.trim().split('').map(cost => typeMapping[cost] || cost);
                moves.push({ name: moveName, power: movePower, cost: moveCost });
            });

            const cardData = { cardID, name, hp, type, weakness, retreatCost, isEx, moves };

            const evolvesFromElement = cardElement.querySelector('.card-text-type a');
            if (evolvesFromElement) {
                cardData.evolvesFrom = evolvesFromElement.innerText.trim();
            }

            cards.push(cardData);
        });

        return { cards, imageUrls };
    });

    const { cards, imageUrls } = data;

    // Ensure the images directory exists
    const imagesDir = path.join(__dirname, '../../assets/cards');
    if (!fs.existsSync(imagesDir)) {
        fs.mkdirSync(imagesDir, { recursive: true });
    }

    // Download images
    // Download and convert images
    await Promise.all(imageUrls.map(async ({ cardID, imageUrl }) => {
        const webpFilePath = path.join(imagesDir, `${cardID}.webp`);
        const pngFilePath = path.join(imagesDir, `${cardID}.png`);
        console.log(`Downloading image from ${imageUrl} to ${webpFilePath}`);
        await downloadImage(imageUrl, webpFilePath);
        console.log(`Downloaded image for ${cardID}`);
        console.log(`Converting ${webpFilePath} to ${pngFilePath}`);
        await convertImageToPng(webpFilePath, pngFilePath);
        console.log(`Converted image for ${cardID}`);
        fs.unlinkSync(webpFilePath); // Remove the webp file after conversion
    }));


    await browser.close();
    return cards;
}

// Example usage
const urlMI = 'https://pocket.limitlesstcg.com/cards/A1a?display=compact';
parseWebsite(urlMI)
    .then(cards => {
        const filePath = path.join(__dirname, 'data', 'mythicalIsland.json');
        fs.writeFileSync(filePath, JSON.stringify(cards, null, 2));
        console.log('Data saved to mythicalIsland.json');
    })
    .catch(error => {
        console.error('Error:', error);
    });

const urlGA = 'https://pocket.limitlesstcg.com/cards/A1?display=compact';
parseWebsite(urlGA)
    .then(cards => {
        const filePath = path.join(__dirname, 'data', 'geneticApex.json');
        fs.writeFileSync(filePath, JSON.stringify(cards, null, 2));
        console.log('Data saved to geneticApex.json');
    })
    .catch(error => {
        console.error('Error:', error);
    });