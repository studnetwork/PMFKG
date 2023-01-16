import { Component, OnInit } from '@angular/core';
import { Movie } from 'src/app/core/models/movie.model';
import { Rating } from 'src/app/core/models/rating.model';
import { AuthService } from 'src/app/core/services/auth.service';
import { RatingService } from 'src/app/core/services/rating.service';

@Component({
  selector: 'app-profile-page',
  templateUrl: './profile-page.component.html'
})
export class ProfilePageComponent implements OnInit {
  
  movies: Array<Movie> = [];

  constructor(
    private ratingService: RatingService,
    private authService: AuthService
  ) {}

  ngOnInit(): void {
    this.ratingService.ratedMovies().subscribe( 
      (movies: Array<Movie>) => {
        this.movies = movies;
    });
  }

  logout() {
    console.log('test')
    this.authService.logout();
  }

  calculateAvgRating(ratings: Array<Rating>): number {
    let sum = 0;

    if(ratings.length == 0)
      return 0;

    ratings.forEach(rating => {
      sum += rating.rating;
    });

    return sum / ratings.length;
  }
}
