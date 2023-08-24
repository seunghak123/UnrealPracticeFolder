using Microsoft.EntityFrameworkCore;
using Portpoli.Models;
namespace Portpoli
{
    public class UserDbContext : DbContext
    {
        public UserDbContext(DbContextOptions<UserDbContext> options)
            : base(options)
        {
        }

        // DbSet<> 속성을 사용하여 데이터베이스 테이블과 매핑합니다.
        public DbSet<LoginViewModel> loginModel { get; set; }
        // 추가 모델 클래스가 있다면 위와 같이 DbSet<>으로 추가합니다.
    }
}