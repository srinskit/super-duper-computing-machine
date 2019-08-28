#include <gcrypt.h>

void log_callback(void *priv, int level, const char *fmt, va_list args) {
    vprintf(fmt, args);
    printf(" ");
}

int main() {
//    gcry_set_log_handler(log_callback, nullptr);

    unsigned char message[] = "HelloWorld\n";
    unsigned message_len = 11;

    unsigned char digest[32];
    gcry_md_hash_buffer(GCRY_MD_SHA256, digest, message, message_len);

    gcry_mpi_t mpi_digest = gcry_mpi_new(256);
    gcry_mpi_scan(&mpi_digest, GCRYMPI_FMT_USG, digest, sizeof(digest), nullptr);

//    unsigned char buff[64 + 1 + 2];
//    gcry_mpi_print(GCRYMPI_FMT_HEX, buff, sizeof(buff), nullptr, mpi_digest);
//    std::cout << buff << std::endl;

    unsigned char mod[] = "FFFFFF";

    gcry_mpi_t mpi_mod = gcry_mpi_new(3 * 8);
    gcry_mpi_scan(&mpi_mod, GCRYMPI_FMT_HEX, mod, 0, nullptr);

    gcry_mpi_t mpi_r = gcry_mpi_new(3 * 8);
    gcry_mpi_mod(mpi_r, mpi_digest, mpi_mod);

//    gcry_mpi_dump(mpi_digest);
//    gcry_mpi_dump(mpi_mod);
    gcry_mpi_dump(mpi_r);
    gcry_mpi_release(mpi_digest);

    return 0;
}