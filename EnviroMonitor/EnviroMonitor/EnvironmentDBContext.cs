using EnviroMonitor.Models;
using Microsoft.EntityFrameworkCore;

namespace EnviroMonitor
{
    public class EnvironmentDBContext: DbContext
    {
        public EnvironmentDBContext(DbContextOptions options) : base(options)
        {
        }

        protected EnvironmentDBContext()
        {
        }
        public DbSet<EnvironmentReading> EnvironmentReadings { get; set; }
    }
}
