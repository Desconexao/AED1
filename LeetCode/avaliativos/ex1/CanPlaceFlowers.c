bool canPlaceFlowers(int *flowerbed, int flowerbedSize, int n) {
    if ((n == 1) && (flowerbedSize == 1) && flowerbed[0] == 0)
        return true;
    // it doesn't have adjacent plots
    for (int i = 1; i < flowerbedSize; i++) {
        if (n == 0)
            break;
        if (i == 1) {
            // first index
            if (flowerbed[0] == 0 && flowerbed[1] == 0) {
                flowerbed[0] = 1;
                n -= 1;
            }
        } else if (i == (flowerbedSize - 1)) {
            // last index
            if (flowerbed[i - 1] == 0 && flowerbed[i] == 0) {
                flowerbed[i] = 1;
                n -= 1;
            }
        } else {
            // ]first, last[
            if (flowerbed[i - 1] == 0 && flowerbed[i + 1] == 0) {
                if (flowerbed[i] != 1) {
                    flowerbed[i] = 1;
                    n -= 1;
                }
            }
        }
    }

    // printf("%d", n);

    if (n == 0)
        return true;
    else
        return false;
}
