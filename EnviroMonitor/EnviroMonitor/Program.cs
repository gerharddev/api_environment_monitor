using EnviroMonitor;
using EnviroMonitor.Models;
using Microsoft.EntityFrameworkCore;
using Microsoft.Extensions.Configuration;

var builder = WebApplication.CreateBuilder(args);

//Config
var configBuilder = new ConfigurationBuilder();
configBuilder.AddJsonFile("appsettings.json");
IConfigurationRoot config = configBuilder.Build();

//Sql Server
builder.Services.AddDbContext<EnvironmentDBContext>(options =>
    options.UseSqlServer(config.GetConnectionString("DefaultConnection")));

//TODO: CORS

// Add services to the container.

builder.Services.AddControllers();
// Learn more about configuring Swagger/OpenAPI at https://aka.ms/aspnetcore/swashbuckle
builder.Services.AddEndpointsApiExplorer();
builder.Services.AddSwaggerGen();

var app = builder.Build();

// Configure the HTTP request pipeline.
if (app.Environment.IsDevelopment())
{
    app.UseSwagger();
    app.UseSwaggerUI();
}

app.Urls.Add("http://*:5000");  //Local ip/port exposed of network

//app.UseHttpsRedirection();

//app.UseAuthorization();

//app.MapControllers();

app.MapPost("/environment_readings", async (EnvironmentReading env, EnvironmentDBContext context) =>
{
    context.EnvironmentReadings.Add(env);
    await context.SaveChangesAsync();

    return Results.Created($"/environment_readings/{env.Id}", env);
})
.WithName("PostEnvironmentReading")
.ProducesValidationProblem()
.Produces<EnvironmentReading>(StatusCodes.Status201Created);

app.Run();
