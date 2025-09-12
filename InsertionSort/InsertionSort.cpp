#include <iostream>     // Für Ein- und Ausgabe
#include <chrono>       // Für Laufzeitmessung
#include <cassert>      // Für Assertions zur Korrektheitsprüfung

/**
 * Überprüft, ob das Subarray data[l...r] korrekt um das Pivot-Element p an Position m partitioniert wurde.
 * - data[m] == p
 * - Alle Elemente links von m sind >= p
 * - Alle Elemente rechts von m sind <= p
 */
bool isPartitioned(int data[], int l, int r, int m, int p) {
    if (data[m] != p) return false;  // Pivot muss an Position m sein

    // Linke Seite prüfen: Alle Elemente >= p
    for (int i = l; i < m; ++i) {
        if (data[i] < p) return false;
    }

    // Rechte Seite prüfen: Alle Elemente <= p
    for (int i = m + 1; i <= r; ++i) {
        if (data[i] > p) return false;
    }

    return true; // Partition ist korrekt
}

/**
 * Partitioniert das Subarray data[l...r] in-place um das Pivot-Element data[l].
 * Ziel: Elemente >= Pivot nach links, <= Pivot nach rechts.
 * Rückgabewert: Neue Position m des Pivot-Elements.
 */
int partition(int data[], int l, int r) {
    int pivot = data[l]; // Erstes Element als Pivot wählen
    int m = l;           // Index m markiert die letzte Position eines Elements >= Pivot

    // Durchlaufe das Array ab l+1
    for (int i = l + 1; i <= r; ++i) {
        if (data[i] >= pivot) {
            ++m;
            std::swap(data[i], data[m]); // Elemente >= Pivot nach links schieben
        }
    }

    // Pivot an seine endgültige Position tauschen
    std::swap(data[l], data[m]);

    // Nach der Partitionierung Korrektheit sicherstellen
    assert(isPartitioned(data, l, r, m, pivot) && "Partitioning failed.");

    return m; // Neue Pivot-Position zurückgeben
}

/**
 * Quicksort-Algorithmus (rekursiv):
 * Sortiert data[l...r] in absteigender Reihenfolge.
 */
void qsort(int data[], int l, int r) {
    if (l >= r) return; // Basisfall: 0 oder 1 Element → nichts zu tun

    int m = partition(data, l, r); // Partitioniere das Array
    qsort(data, l, m - 1);         // Sortiere linke Seite
    qsort(data, m + 1, r);         // Sortiere rechte Seite
}

/**
 * Überprüft, ob das Array data[0...size-1] **absteigend** sortiert ist.
 * Rückgabewert: true wenn korrekt sortiert, sonst false.
 */
bool isSorted(const int data[], int size) {
    for (int i = 1; i < size; ++i) {
        if (data[i] > data[i - 1]) return false; // Absteigend: kein Element darf größer als sein Vorgänger sein
    }
    return true;
}

/**
 * Hauptprogramm:
 * - Liest Eingabegröße und Elemente vom Benutzer
 * - Gibt Array aus (wenn < 20 Elemente)
 * - Führt Quicksort aus und misst die Laufzeit
 * - Gibt sortiertes Array und Zeit aus
 */
int main() {
    int n;
    std::cin >> n; // Anzahl der Elemente einlesen

    int* arr = new int[n]; // Dynamisches Array für Eingabe

    // Elemente einlesen
    for (int i = 0; i < n; ++i) {
        std::cin >> arr[i];
    }

    // Ausgabe vor dem Sortieren (nur bei kleinen Arrays)
    if (n < 20) {
        std::cout << "Input Array:\n";
        for (int i = 0; i < n; ++i)
            std::cout << arr[i] << (i < n - 1 ? ", " : "\n");
    }

    // Startzeit messen
    auto start = std::chrono::high_resolution_clock::now();

    // Quicksort anwenden
    qsort(arr, 0, n - 1);

    // Endzeit messen
    auto end = std::chrono::high_resolution_clock::now();

    // Dauer berechnen (in Mikrosekunden)
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);

    // Nach dem Sortieren überprüfen, ob korrekt sortiert
    assert(isSorted(arr, n) && "Sorting failed.");

    // Sortiertes Array ausgeben
    std::cout << "After sorting:\n";
    for (int i = 0; i < n; ++i)
        std::cout << arr[i] << (i < n - 1 ? ", " : "\n");

    // Zeit ausgeben
    std::cout << "Time: " << duration.count() << " µs\n";

    delete[] arr; // Speicher freigeben
    return 0;
}
