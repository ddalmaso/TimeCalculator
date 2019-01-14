import java.lang.*;

public class DataSett extends Data {
    private int giorno_settimana;

    public DataSett() {
		int t[] = { 0, 3, 2, 5, 0, 3, 5, 1, 4, 6, 2, 4 };
		int y = Anno(); y -= Mese() < 3? Mese():0;
		giorno_settimana = (y + y/4 - y/100 + y/400 + t[Mese()-1] + Giorno()) % 7;
    }

    public int GiornoSettimana() { return giorno_settimana; }

    public String toString() { //overrides
		int t[] = { 0, 3, 2, 5, 0, 3, 5, 1, 4, 6, 2, 4 };
		int y = Anno(); y -= Mese() < 3? Mese():0;
		return Settimana[(y + y/4 - y/100 + y/400 + t[Mese()-1] + Giorno()) % 7];
    }
}
