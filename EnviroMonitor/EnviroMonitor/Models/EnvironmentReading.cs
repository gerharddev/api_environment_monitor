namespace EnviroMonitor.Models
{
    public class EnvironmentReading
    {
        //TODO: Change from string to decimal
        public Guid Id { get; set; }
        /// <summary>
        /// MQ135
        /// </summary>
        public string RZero { get; set; }
        public string CorrectedRZero { get; set; }
        public string Resistance { get; set; }
        public string PPM { get; set; }
        /// <summary>
        /// DHT
        /// </summary>
        public string Temperature { get; set; }
        public string Humidity { get; set; }

    }
}
