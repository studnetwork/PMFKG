import { Component, OnInit } from '@angular/core';
import { Router } from '@angular/router';
import { Actor } from 'src/app/core/models/actor.model';
import { Movie } from 'src/app/core/models/movie.model';
import { ActorService } from 'src/app/core/services/actor.service';
import { AuthService } from 'src/app/core/services/auth.service';
import { MovieService } from 'src/app/core/services/movie.service';
import { RatingService } from 'src/app/core/services/rating.service';

@Component({
  selector: 'app-dashboard-page',
  templateUrl: './dashboard-page.component.html'
})
export class DashboardPageComponent implements OnInit {

  movies: Array<Movie> = [];
  actors: Array<Actor> = [];
  showActors = false;
  ratings: Array<number> = [];
  
  constructor(
    private router: Router,
    private authService: AuthService,
    private movieService: MovieService,
    private ratingService: RatingService
  ) {}

  ngOnInit(): void {
    this.movieService.getAll().subscribe( (movies: Array<Movie>) => {
      this.movies = movies;

      for (let i = 0; i < movies.length; i++)
        this.ratings.push(0);
    });
  }

  isAuthenticated(): boolean {
    return this.authService.isAuthenticated();
  }

  logout() {
    this.authService.logout();
    this.router.navigateByUrl('/login');
  }

  ratingChange(index: number, event: any) {
    this.ratings[index] = Number.parseInt(event?.target.value);
  }

  getAllActorsForMovieId(movieId: string) {
    let movie = this.movies.find(movie => movie._id == movieId);
    console.log(movie)
    
    if(movie == null)
      this.actors = [];
    else
      this.actors = movie.actors;

    this.showActors = true;
  }

  rate(movieId: string, index: number) {
    this.ratingService.rateMovie(movieId, this.ratings[index]).subscribe(ratedSuccessfully => {
      console.log(ratedSuccessfully)
    });
  }
}
