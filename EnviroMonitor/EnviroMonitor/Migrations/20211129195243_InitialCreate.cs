using System;
using Microsoft.EntityFrameworkCore.Migrations;

#nullable disable

namespace EnviroMonitor.Migrations
{
    public partial class InitialCreate : Migration
    {
        protected override void Up(MigrationBuilder migrationBuilder)
        {
            migrationBuilder.CreateTable(
                name: "EnvironmentReadings",
                columns: table => new
                {
                    Id = table.Column<Guid>(type: "uniqueidentifier", nullable: false),
                    RZero = table.Column<string>(type: "nvarchar(max)", nullable: false),
                    CorrectedRZero = table.Column<string>(type: "nvarchar(max)", nullable: false),
                    Resistance = table.Column<string>(type: "nvarchar(max)", nullable: false),
                    PPM = table.Column<string>(type: "nvarchar(max)", nullable: false),
                    Temperature = table.Column<string>(type: "nvarchar(max)", nullable: false),
                    Humidity = table.Column<string>(type: "nvarchar(max)", nullable: false)
                },
                constraints: table =>
                {
                    table.PrimaryKey("PK_EnvironmentReadings", x => x.Id);
                });
        }

        protected override void Down(MigrationBuilder migrationBuilder)
        {
            migrationBuilder.DropTable(
                name: "EnvironmentReadings");
        }
    }
}
